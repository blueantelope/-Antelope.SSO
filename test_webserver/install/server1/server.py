#!/usr/bin/env python
import os
import sys

pidname = ".pid"

def main():
  global pidname
  command = sys.argv[1]
  curdir = os.getcwd()
  pidfile = os.path.join(curdir, pidname)
  if command == "start":
    fp = open(pidfile, "a")
    fp.write(str(os.getpid()) + " ")
    fp.close()
    argv = []
    n = 0
    for a in sys.argv:
      if n == 1:
        argv.append("runserver")
      else:
        argv.append(a)
      n = n + 1
    run(argv)
  if command == "stop":
    if os.path.exists(pidfile):
      fp = open(pidfile, "r")
      ss = fp.readline()
      for s in ss.split(" "):
        try:
          if len(s) > 0:
            os.system("kill -9 " + s)
        except exception:
            print("exception when kill " + s)
      fp.close()
      os.remove(pidfile)

def run(argv):
  os.environ.setdefault("DJANGO_SETTINGS_MODULE", "webserver.settings")
  from django.core.management import execute_from_command_line
  execute_from_command_line(argv)

if __name__ == "__main__":
  main()
