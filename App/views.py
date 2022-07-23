import json
from pyexpat.errors import messages
from urllib import response
from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt
from django.core import serializers
from django.contrib import messages
from django.contrib.auth.models import User,auth
from django.shortcuts import render, redirect

from weather.models import sensor
Config = {
  "apiKey": "AIzaSyCCRcqLnY7rMWRkC0xM4P5x58cHeRL9NIc",
  "authDomain": "weather-9f439.firebaseapp.com",
  "projectId": "weather-9f439",
  "storageBucket": "weather-9f439.appspot.com",
  "messagingSenderId": "595353570423",
  "appId": "1:595353570423:web:061f0ae4aae1da3a29ca72",
  "measurementId": "G-0B62LLNEJN"
}
# firebase=pyrebase

@csrf_exempt
def sensor_view(request):
    if request.method == 'POST':
       
        data=request.body.decode('utf-8')
        dict = json.loads(data)
        print(dict)
        
        id = dict['device_id']
        t = dict['temp_reading']
        h = dict['hum_reading']
        p= dict['pressure_reading']
        temp1=dict['temp1_reading']
        moist = dict['moisture_value']
        
        sensor.objects.create(device_id=id, temp=t, hum=h,pressure=p,p_temp=temp1,moisture=moist) 


        #     data=request.body.decode('utf-8')
        #     dict = json.loads(data)
        #     print(dict)
        #     id1=dict['device_id']
        #     temp1 = dict['temp_reading1']
        #     print(temp1)
        #     hum1 = dict['hum_reading1']
        #     gas_analog1 = dict['gas_analog_reading1']
        #     device_status=dict['device_status']
        #     if device_status == '1':
        #         status=True
        #     else:
        #         status=False
        #     print(status)
            
        #     secondSensor_reading.objects.create(device_id1=id1, temp_reading1=temp1, hum_reading1=hum1,device_status1=status, gas_analog_reading1=gas_analog1)
            
    
    # if request.accepts("application/json"):
    #     obj=Sensor_reading.objects.last()
    #     device_id=obj.device_id
    #     temp_reading=obj.temp_reading
    #     hum_reading=obj.hum_reading
    #     smoke_reading=obj.gas_analog_reading
    #     device_status=obj.device_status
    #     print(device_status)
    #     obj1=secondSensor_reading.objects.last()
    #     device_id1=obj1.device_id1
    #     temp_reading1=obj1.temp_reading1
    #     hum_reading1=obj1.hum_reading1
    #     smoke_reading1=obj1.gas_analog_reading1
    #     device_status1=obj1.device_status1
    #     response={"id":device_id,"temp":temp_reading,"hum":hum_reading,"smoke":smoke_reading,"status":device_status,"id1":device_id1,"temp1":temp_reading1,"hum1":hum_reading1,"smoke1":smoke_reading1,"status1":device_status1}
        
        
    
                

            # Import the required module for text
    # to speech conversion
            
            # os.system("mpg321 welcome.mp3")

            # welcome=open(r"welcome.mp3",'rb')
            # # welcome_sound=welcome.readframes(-1)
            
            # bot.sendVoice(
            # chat_id="@%s" % telegram_settings['channel_name'],voice=welcome
            # )
       

    return render(request,"display.html",{})
def display_view(request):
    var=sensor.objects.last()
    id=var.device_id
    t=var.temp
    h=var.hum
    p=var.pressure
    te=var.p_temp
    m=var.moisture
    response={"id":id,"temp":t,"hum":h,"pressure":p,"p_temp":te,"moisture":m}
    
    return JsonResponse(response)


def weather_view(request):
    
    return render(request,"weather.html",{})
def weather_map_view(request):
    var=sensor.objects.last()
    id=var.device_id
    t=var.temp
    h=var.hum
    p=var.pressure
    te=var.p_temp
    m=var.moisture
    response={"id":id,"temp":t,"hum":h,"pressure":p,"p_temp":te,"moisture":m}
    return JsonResponse({"obj":response})
def home_view(request):
    return render(request,"home.html",{})
def login_view(request):
    return render(request,"login.html",{})
def button_view(request):
    return render(request,"button.html",{})


  



        


    