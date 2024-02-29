from rest_framework import serializers
from .models import Transaction
from account.serializers import AccountSerializer
from customer.serializers import CustomerSerializer


class TransactionSerializer(serializers.ModelSerializer):
    account = AccountSerializer(read_only=True)
    customer = CustomerSerializer(read_only=True)
    date = serializers.DateField()
    volume = serializers.FloatField()

    class Meta:
        model = Transaction
        fields = (
            "id",
            "account",
            "customer",
            "date",
            "volume",
        )
