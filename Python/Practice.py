args = input()
match args:
    case ['gcc']:
        print('missing file')
    case ['gcc', file1, *file2]
        print('gcc ' + file1 + ' '.join(file2))
    case _:
        print('invalid arguments')
    
