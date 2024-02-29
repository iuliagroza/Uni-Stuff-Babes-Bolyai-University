from django.db import models


class Customer(models.Model):
    name = models.CharField(max_length=255)
    phone = models.CharField(max_length=15)
    email = models.CharField(max_length=255)
    address = models.TextField()
    total_savings = models.FloatField()
    total_loans = models.FloatField()
    accounts = models.ManyToManyField(
        "account.Account", through="transaction.Transaction"
    )
