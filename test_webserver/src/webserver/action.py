
from django.http import HttpRequest
from django.http import HttpResponse

class SsoSession:
  keys = ['sessionid', 'domain', 'tokenid', 'logon']
  values = {}
  _debug = False

  def __init__(self, _debug):
    self._debug = _debug

  def put(self, info):
    if info is not None:
      for k, v in info.items():
        for dk in self.keys:
          if dk == k:
            self.values[k] = info[k]
    if (self._debug):
      self.debug()
  
  def debug(self):
    for k, v in self.values.items():
      if self.values[k] is not None:
        print(k + '=' + str(v))

  def tostr(self):
    s = ''
    for k, v in self.values.items():
      if self.values[k] is not None:
        s += k + '=' + str(v)
    return s

class SsoSender:
  sso_ip = '127.0.0.1'
  sso_port = 10926
  sso_password = ''
  connecter = None

  def __init__(self, args):
    if args is not None:
      self.sso_ip = args.server_ip
      self.sso_port = args.server_port
      self.sso_password = args.server_port

  def connect(self):
    import socket
    self.connecter = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    self.connecter.connect((self.sso_ip, int(self.sso_port)))

  def verify(self, session):
    if self.connecter is None:
      self.connect()
    print "=============verify================"
    print "send:"
    print "\t"+session.tostr()
    self.connecter.send(session.tostr())
    print "receive:"
    print "\t"+self.connecter.recv(1024)
    print "===================================="


sso_session = SsoSession(True)
sso_sender = SsoSender(None)

def index(request):
  msg = 'no logon</br>'
  if logon(request):
    msg = 'logon</br>'
  msg += sessionContent(request)
  sso_session.put({'sessionid':request.session.session_key})
  sso_sender.verify(sso_session)
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
      print(Exception, e)
      msg = 'Exception', e
  msg += '</br>' + sessionContent(request)
  sso_session.put({'logon':True})
  return HttpResponse(msg)

def logon(request):
  if request.session.get('logon'):
    return True
  return False

def sessionContent(request):
  session = request.session
  s = '=======================session=======================</br>'
  s += session.session_key + '</br>'
  for k, v in session.items():
    s += k + '=' + str(v) + '</br>'
  s += '=====================================================</br>'
  return s
