#!/usr/bin/env python
#encoding: utf8

from django.http import HttpRequest
from django.http import HttpResponse
import struct
import array
import binascii

class Header:
  def __init__(self, argp):
    self.version = 1
    if argp['version'] is not None:
      self.version = argp['version']
    self.sn = argp['sn']
    self.action = argp['action']
    self.password = argp['password']
    self.dlen = len(argp['domain'])
    self.domain = argp['domain']
    self.num = 0

  def toPacket(self):
    format = '!b'
    n = 0
    while n < 14:
      format = format + 'b'
      n = n + 1
    format = format + 'b16sH' + str(self.dlen) + 'sH'
    values = [self.version]
    for c in self.sn:
      values.append(int(c))
    values.extend([self.action, self.password, self.dlen, self.domain, self.num])
    s = struct.Struct(format)
    packet = s.pack(*values)
    return packet

  def size(self):
    return 1 + 14 + 1 + 16 + self.dlen + 2

class SsoSession:
  keys = ['sessionid', 'domain', 'tokenid', 'logon']
  values = {}
  _debug = False

  def __init__(self, argp):
    self.header = Header(argp['header'])
    if argp['debug'] is not None:
      self._debug = argp['debug']

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

  def bodyNum(self):
    return len(self.values)

  def toBodyPacket(self):
    body_packet = ''
    for k, v in self.values.items():
      content = str(k) + '=' + str(v)
      clen = len(content)
      format = '!H' + str(clen) + 's'
      body_packet = body_packet + struct.pack(format, clen, content)
    return body_packet

  def toPacket(self):
    self.header.num = self.bodyNum()
    header_packet = self.header.toPacket()
    body_packet = self.toBodyPacket()
    return header_packet + body_packet

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
    print '=============verify================'
    packet = session.toPacket()
    print 'send packet: ' + repr(packet)
    self.connecter.send(packet)
    print 'receive:'
    print '\t' + self.connecter.recv(1024)
    print '===================================='

sso_session = SsoSession({
  'header': {
    'version': 1,
    'sn': '22222222222222',
    'action': 1,
    'password': '3333333333333333',
    'domain': 'www.blueantelope'
  },
  'debug': True
})
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
  s += str(session.session_key) + '</br>'
  for k, v in session.items():
    s += k + '=' + str(v) + '</br>'
  s += '=====================================================</br>'
  return s
