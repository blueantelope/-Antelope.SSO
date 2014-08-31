
from django.http import HttpRequest
from django.http import HttpResponse
from django.contrib import admin

def index(request):
  msg = 'no logon'
  if logon(request):
    msg = 'logon'
  return HttpResponse(msg)

def login(request):
  print('enter login')
  msg = 'login failed'
  if logon(request):
    msg = 'logon'
  else:
    try:
      username = request.GET['username']
      password = request.GET['password']
      if username == 'admin' and password == 'admin':
        request.session['logon'] = True
        msg = 'login success'
    except Exception, e:
      print Exception, e
      msg = 'Exception', e
  return HttpResponse(msg)

def logon(request):
  if request.session.get('logon'):
    return True
  return False
