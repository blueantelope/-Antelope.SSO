from django.conf.urls import patterns, include, url

from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    url(r'^$', 'webserver.action.index'),
    url(r'^login', 'webserver.action.login'),
)
