import gzip
import os
import io

name = 'sample.txt.gz'  # change to decrypted file

with gzip.open(name, 'rb') as ip:
    with io.TextIOWrapper(ip, encoding='utf-8') as decoder:
        # Let's read the content using read()
        content = decoder.read()
        print(content)

print(f"The file Sample.txt contains {os.stat('Sample.txt').st_size} bytes")