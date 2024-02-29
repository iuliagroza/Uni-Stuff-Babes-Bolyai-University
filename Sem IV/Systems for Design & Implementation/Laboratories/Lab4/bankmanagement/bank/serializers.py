from rest_framework import serializers
from django.core.validators import MinValueValidator
from .models import Bank, BankQuery


class BankSerializer(serializers.ModelSerializer):
    class Meta:
        model = Bank
        fields = "__all__"

    def validate_total_assets(self, value):
        if value < 0:
            raise serializers.ValidationError("Assets should always be positive.")
        return value

    def validate_total_equity(self, value):
        if value < 0:
            raise serializers.ValidationError("Equity should always be positive.")
        return value
