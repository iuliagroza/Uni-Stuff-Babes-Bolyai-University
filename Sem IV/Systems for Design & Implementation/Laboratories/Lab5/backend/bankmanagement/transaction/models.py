from django.db import models


class Transaction(models.Model):
    account = models.ForeignKey("account.Account", on_delete=models.CASCADE)
    customer = models.ForeignKey("customer.Customer", on_delete=models.CASCADE)
    date = models.DateField(auto_now_add=True)
    # If volume is received, the value is positive, if volume is sent, the value is negative
    volume = models.FloatField()
