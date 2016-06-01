import os
import re 

env = Environment(UIPATH='#/ui',
                  QT_CPPPATH='/usr/include/qt5',
                  QT_LIB='qt-mt',
                  QT_LIBPATH='/usr/lib64/qt5/',
                  QT_BINPATH='/usr/lib64/qt5/bin',
                  QT_UICCOM = [ ['$QT_UIC', '$QT_UICDECLFLAGS', '-o', '${TARGETS[0]}', '$SOURCE'],
            ['$QT_UIC', '$QT_UICIMPLFLAGS', '', '', '-o', '${TARGETS[1]}', '$SOURCE'],
           ['$QT_MOC', '$QT_MOCFROMHFLAGS', '-o', '${TARGETS[2]}', '${TARGETS[0]}']],
                  tools= ['default', 'qt'],
                  CCFLAGS='-ggdb -fPIC -std=c++11 -Wl,rpath=./',
                  LIBPATH=['/usr/local/lib'])


## .ui Scanner, built-in doesn't let you add paths in a clear manner 

# ui_re = re.compile(r'.*\.ui$')

# def ui_scan(node, env, path, arg):
# #    print 'uiScanner Node: {0}, Path: {1}'.format(node, path[0])
#     contents = node.rstr()
#     uis = ui_re.findall(contents)
#     paths = [] 
#     for ui in uis: 
#         for d in path:
#             fname = str(d)+os.sep+ui
#             print fname
#             if os.path.exists(fname):
#                 paths.append(fname)

#     return paths



# pathFn = FindPathDirs('UIPATH')


# uiscan = Scanner(function = ui_scan,
#                  argument = None,
#                  skeys=['.ui'],
#                  path_function=FindPathDirs('UIPATH'))

                 

# env.Append(SCANNERS=uiscan)

#print env.Dump()

SConscript(['src/SConscript'])

