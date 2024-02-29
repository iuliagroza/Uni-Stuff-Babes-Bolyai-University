from django.db import models


class Bank(models.Model):
    name = models.CharField(max_length=255)
    bicswift = models.CharField(max_length=18)
    address = models.TextField()
    total_assets = models.FloatField()
    total_equity = models.FloatField()
