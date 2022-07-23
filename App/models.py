from django.db import models

# Create your models here.
class sensor(models.Model):
    device_id=models.IntegerField()
    temp=models.FloatField(max_length=25,null=True)
    hum=models.FloatField(max_length=25,null=True)
    pressure=models.FloatField(max_length=25)
    p_temp=models.FloatField(max_length=20)
    moisture=models.IntegerField()
    
