from django.db import models


class Bank(models.Model):
    name = models.CharField(max_length=255)
    bicswift = models.CharField(max_length=18)
    headquarters = models.CharField(max_length=255)
    ceo = models.CharField(max_length=255)
    total_assets = models.FloatField()
    total_equity = models.FloatField()


class BankQuery(models.Model):
    bank = models.OneToOneField(
        Bank,
        on_delete=models.CASCADE,
    )
    no_branches = models.IntegerField()
