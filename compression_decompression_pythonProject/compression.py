import gzip
import os
import io

name = 'sample.txt.gz'

with gzip.open(name, 'wb') as output:
    # We cannot directly write Python objects like strings!
    # We must first convert them into a bytes format using io.BytesIO() and then write it
    with io.TextIOWrapper(output, encoding='utf-8') as encode:
        encode.write('This is a sample text')

# Let's print the updated file stats now
print(f"The file {name} now contains {os.stat(name).st_size} bytes")