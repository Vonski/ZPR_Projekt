from subprocess import call

call('.\\bin\\packfolder.exe .\\res resources.cpp -v \"resources\"', shell=True)

env = Environment(CCFLAGS=['/EHsc', '/D_WINDLL'], CPPPATH=['./include/'], LIBS=['user32.lib', 'ole32.lib', 'shell32.lib'])


src_files = ['main.cpp', './include/sciter-win-main.cpp']
name = 'ZPR'
env.Program(name, src_files)