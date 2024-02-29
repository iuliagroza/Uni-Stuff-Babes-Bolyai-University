from rest_framework import serializers
from .models import Branch
from bank.serializers import BankSerializer


class BranchSerializer(serializers.ModelSerializer):
    name = serializers.CharField(max_length=255)
    bicswift = serializers.CharField(max_length=18)
    address = serializers.CharField()
    total_assets = serializers.IntegerField(read_only=True)
    total_equity = serializers.IntegerField(read_only=True)
    bank = BankSerializer(read_only=True)

    class Meta:
        model = Branch
        fields = (
            "id",
            "name",
            "bicswift",
            "address",
            "total_assets",
            "total_equity",
            "bank",
        )
