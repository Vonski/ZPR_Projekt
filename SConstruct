from subprocess import call
import glob
import os

if os.name!="posix":
	call('.\\bin\\packfolder.exe .\\res .\\res\\resources.cpp -v \"resources\"', shell=True)

	env = Environment(CCFLAGS=['/EHsc', '/D_WINDLL'], CPPPATH=['./include/sciter/', './res/', './include/boost/include/boost-1_66/', './src/'], LIBS=['user32.lib', 'ole32.lib', 'shell32.lib'], LIBPATH='./include/boost/lib/')


	src_files = glob.glob('./src/*.cpp')
	src_files.append('./include/sciter/sciter-win-main.cpp');
	name = 'ZPR'
	target = env.Program(name, src_files)

	SConscript(['tests/SConscript'])
else:
	call('./bin/packfolder ./res ./res/resources.cpp -v \"resources\"', shell=True)
	
	env = Environment(CPPPATH=['./include/sciter/', './res/', './include/boost/include/boost-1_66/', './src/'], LIBPATH=['./include/boost/lib/'], LIBS=['-ldl'])
	env.ParseConfig(['pkg-config --cflags gtk+-3.0', 'pkg-config --libs gtk+-3.0'])

	src_files = glob.glob('./src/*.cpp')
	src_files.append('./include/sciter/sciter-gtk-main.cpp');
	src_files.remove('./src/WindowsCollector.cpp')
	name = 'ZPR'
	target = env.Program(name, src_files)

	SConscript(['tests/SConscript'])

Clean(target, './res/resources.cpp')
