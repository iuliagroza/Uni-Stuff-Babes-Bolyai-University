from rest_framework import serializers
from .models import Bank, BankQuery


class BankSerializer(serializers.ModelSerializer):
    class Meta:
        model = Bank
        fields = "__all__"


class BankQuerySerializer(serializers.ModelSerializer):
    class Meta:
        model = BankQuery
        fields = "__all__"
