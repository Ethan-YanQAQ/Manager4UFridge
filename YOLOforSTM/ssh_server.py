"""SSH helper for remote server."""
import paramiko
import sys

HOST = '223.109.239.36'
PORT = 10220
USER = 'root'
PASS = 'Xuiquoh9'

def run(cmd, timeout=30):
    c = paramiko.SSHClient()
    c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    c.connect(HOST, port=PORT, username=USER, password=PASS, timeout=10)
    stdin, stdout, stderr = c.exec_command(cmd, timeout=timeout)
    out = stdout.read().decode(errors='replace')
    err = stderr.read().decode(errors='replace')
    c.close()
    if err:
        print(f'[ERR] {err}', file=sys.stderr)
    print(out)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python ssh_server.py "<command>"')
        sys.exit(1)
    run(sys.argv[1])
