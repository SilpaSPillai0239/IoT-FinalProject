"""weathermonitoring URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path,include


from weather.views import button_view, display_view, home_view, login_view, sensor_view, weather_map_view,weather_view

urlpatterns = [
    path('admin/', admin.site.urls),
     path('readings',sensor_view,name="sensor"),
     path('display',display_view,name="display"),
      path('weather',weather_view,name="weather"),
       path('weatherdetails',weather_map_view,name="weather_details"),
    path('home',home_view,name="home"),
    path('login',login_view,name="login"),
    path('button',button_view,name="button")

     
     
]
