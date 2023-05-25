import os

path = os.getcwd()
pathlen = len(path)

srcroots = []
headroots = []
srcfiles = []

for root, dirs, files in os.walk(path):
    temp = []
    withhead = False
    if files != []:
        for srcfile in files:
            if srcfile.endswith(".c"):
                temp.append(srcfile)
            elif srcfile.endswith(".h"):
                withhead = True
        root = root[pathlen:]
        root = root.replace("\\","/")
        if temp != []:
            srcroots.append(root)
            srcfiles.append(temp)
        if withhead == True:
            headroots.append(root)

index = 0
with open('CMakeLists.txt', 'w', encoding='utf-8') as f:
    f.write("idf_component_register(\n")
    f.write("    SRCS\n")
    for strroots in srcroots:
        for strfiles in srcfiles[index]:
            f.write('        \".')
            f.write(strroots)
            f.write('/')
            f.write(strfiles)
            f.write('\"\n')
        index = index + 1
    f.write("\n    INCLUDE_DIRS\n")
    for strheads in headroots:
        f.write('        \".')
        f.write(strheads)
        f.write('\"\n')
    f.write(")")
    f.close()

