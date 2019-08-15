from django.urls import path
from django.conf.urls import url
from django.conf.urls import include
from . import views


urlpatterns = [
    path('', views.index, name='index'),
    #path('signin/', views.signin, name='signin'),
    #path('signup/', views.signup, name='signup'),
    #path('terms/', views.terms, name='terms'),
    url(r'^accounts/', include('allauth.urls')),
]