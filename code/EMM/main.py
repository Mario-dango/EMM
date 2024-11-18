import os
import re
import win32crypt  # Requires pywin32 package

_group = '(?P<{}>{}+)'
WORKBENCH_PATTERN = '{dbm}@{host}:{port}\2{user}\3{password}'.format(
    dbm=_group.format('dbm', r'\w'),
    host=_group.format('host', r'[\w\.-]'),
    port=_group.format('port', r'\d'),
    user=_group.format('user', r'[\w\.-]'),
    password=_group.format('password', '.'),
)

def read_workbench_user_data(file_path=None):
    if file_path is None:
        file_path = os.path.join(os.getenv('APPDATA'), 'MySQL/Workbench/workbench_user_data.dat')
    print("2")
    with open(file_path, 'rb') as file:
        encrypted_data = file.read()
    decrypted_data = win32crypt.CryptUnprotectData(encrypted_data, None, None, None, 0)
    decrypted_content = decrypted_data[1].decode('utf-8')
    print(decrypted_content)
    return decrypted_content.split('\n')[:-1]

if __name__ == '__main__':
    print("hola")
    for item in read_workbench_user_data():
        print("antes del match")
        match = re.match(WORKBENCH_PATTERN, item)

        print(f'{match.group("dbm")}:')
        print(f'\tHost: {match.group("host")}:{match.group("port")}')
        print(f'\tUsername: {match.group("user")}')
        print(f'\tPassword: {match.group("password")}')