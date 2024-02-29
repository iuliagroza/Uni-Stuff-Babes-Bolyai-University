from rest_framework import serializers
from .models import Customer
from django.core.validators import validate_email
from django.core.exceptions import ValidationError
from account.serializers import AccountSerializer


class CustomerSerializer(serializers.ModelSerializer):
    name = serializers.CharField(max_length=255)
    phone = serializers.CharField(max_length=15)
    email = serializers.CharField(max_length=255)
    address = serializers.CharField(max_length=255)
    total_savings = serializers.FloatField(read_only=True)
    total_loans = serializers.FloatField(read_only=True)
    accounts = AccountSerializer(many=True)

    class Meta:
        model = Customer
        fields = (
            "id",
            "name",
            "phone",
            "email",
            "address",
            "total_savings",
            "total_loans",
            "accounts",
        )

    def validate(self, data):
        try:
            validate_email(data.get("email"))
            return data
        except ValidationError:
            raise serializers.ValidationError("Wrong email format.")


class CustomerBalanceSerializer(serializers.ModelSerializer):
    name = serializers.CharField(max_length=255)
    phone = serializers.CharField(max_length=15)
    email = serializers.CharField(max_length=255)
    address = serializers.CharField(max_length=255)
    total_savings = serializers.FloatField(read_only=True)
    total_loans = serializers.FloatField(read_only=True)
    total_balance = serializers.FloatField(read_only=True)

    class Meta:
        model = Customer
        fields = (
            "id",
            "name",
            "phone",
            "email",
            "address",
            "total_savings",
            "total_loans",
            "total_balance",
        )
