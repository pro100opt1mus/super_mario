"""Unix PTY verification of startup/input/exit, or the real-main replay target."""
import argparse
import fcntl
import os
from pathlib import Path
import pty
import select
import struct
import subprocess
import termios
import time

parser = argparse.ArgumentParser()
parser.add_argument('binary')
parser.add_argument('--replay', action='store_true')
parser.add_argument('--output', default='console-check')
args = parser.parse_args()
master, slave = pty.openpty()
fcntl.ioctl(slave, termios.TIOCSWINSZ, struct.pack('HHHH', 35, 210, 0, 0))
before = termios.tcgetattr(slave)
env = dict(os.environ, TERM='xterm-256color')
process = subprocess.Popen([args.binary], stdin=slave, stdout=slave, stderr=slave, env=env)
output = bytearray()

def read_for(seconds):
    until = time.monotonic() + seconds
    while time.monotonic() < until:
        ready, _, _ = select.select([master], [], [], min(.05, max(0, until-time.monotonic())))
        if ready:
            try:
                output.extend(os.read(master, 65536))
            except OSError:
                break
        if process.poll() is not None:
            break

try:
    if args.replay:
        read_for(115)
    else:
        read_for(1.5)
        for key, seconds in [(b'a',4.5),(b' ',.8),(b'd',.8),(b's',.3),(b'q',.5)]:
            os.write(master, key)
            read_for(seconds)
    if process.poll() is None:
        process.terminate()
        raise RuntimeError('Program did not exit within the allowed time')
    code = process.wait()
    # Drain the final terminal restoration and sanitizer diagnostics.
    while select.select([master], [], [], .05)[0]:
        output.extend(os.read(master, 65536))
    after = termios.tcgetattr(slave)
    differences = [(i,a,b) for i,(a,b) in enumerate(zip(before,after)) if a != b]
    # PENDIN is a transient tty input-retype flag set by macOS, not a mode.
    before[3] &= ~getattr(termios, 'PENDIN', 0)
    after[3] &= ~getattr(termios, 'PENDIN', 0)
    restored = before == after
    entered = b'\x1b[?1049h' in output
    exited = b'\x1b[?1049l' in output
    complete = b'GAME COMPLETE' in output
    clean = b'ERROR: AddressSanitizer' not in output and b'runtime error:' not in output
    Path(args.output+'.ansi').write_bytes(output)
    report = (f'exit_code={code}\noutput_bytes={len(output)}\nterminal_modes_restored={restored}\n'
              f'alternate_screen_enter={entered}\nalternate_screen_exit={exited}\n'
              f'game_complete_displayed={complete}\nno_sanitizer_diagnostics={clean}\n'
              f'raw_termios_differences={differences}\n')
    Path(args.output+'.log').write_text(report)
    print(report)
    assert code == 0 and restored and entered and exited and clean
    if args.replay:
        assert complete, 'The real main did not reach GAME COMPLETE'
finally:
    if process.poll() is None:
        process.terminate()
        process.wait()
    os.close(master)
    os.close(slave)
