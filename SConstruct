from subprocess import call

call('.\\bin\\packfolder.exe .\\res .\\res\\resources.cpp -v \"resources\"', shell=True)

env = Environment(CCFLAGS=['/EHsc', '/D_WINDLL'], CPPPATH=['./include/sciter/', './res/'], LIBS=['user32.lib', 'ole32.lib', 'shell32.lib'])


src_files = ['./src/main.cpp', './include/sciter/sciter-win-main.cpp']
name = 'ZPR'
target = env.Program(name, src_files)

Clean(target, 'resources.cpp')