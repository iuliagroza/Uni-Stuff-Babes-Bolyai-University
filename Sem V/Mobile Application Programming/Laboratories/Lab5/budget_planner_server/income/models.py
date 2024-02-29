from django.db import models

class Income(models.Model):
    amount = models.FloatField()
    date = models.DateField()
    category = models.CharField(max_length=100)
    note = models.TextField()
