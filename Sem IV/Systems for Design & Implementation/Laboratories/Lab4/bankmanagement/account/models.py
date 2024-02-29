from django.db import models
from branch.models import Branch


class Account(models.Model):
    name = models.CharField(max_length=255)
    iban = models.CharField(max_length=34)
    bicswift = models.CharField(max_length=11)
    balance = models.FloatField()
    currency = models.CharField(max_length=3)
    branch = models.ForeignKey(
        Branch, null=True, default=None, on_delete=models.CASCADE
    )
    customers = models.ManyToManyField(
        "customer.Customer", through="transaction.Transaction"
    )
