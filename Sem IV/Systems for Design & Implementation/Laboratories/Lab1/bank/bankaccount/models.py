from django.db import models


class BankAccount(models.Model):
    name = models.CharField(max_length=255)
    iban = models.CharField(max_length=34)
    bicswift = models.CharField(max_length=11)
    balance = models.FloatField()
    currency = models.CharField(max_length=3)
