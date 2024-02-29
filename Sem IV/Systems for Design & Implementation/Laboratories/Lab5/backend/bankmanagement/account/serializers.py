from rest_framework import serializers
from .models import Account
from branch.serializers import BranchSerializer


class AccountSerializer(serializers.ModelSerializer):
    name = serializers.CharField(max_length=255)
    iban = serializers.CharField(max_length=34)
    bicswift = serializers.CharField(max_length=11)
    balance = serializers.FloatField()
    currency = serializers.CharField(max_length=3)
    branch = BranchSerializer(read_only=True)

    class Meta:
        model = Account
        fields = (
            "id",
            "name",
            "iban",
            "bicswift",
            "balance",
            "currency",
            "branch",
        )

    def validate_iban(self, value):
        special_chars = ["!", "@", "#", "$", "%", "^", "&", "*", "(", ")"]
        for char in special_chars:
            if char in value:
                raise serializers.ValidationError(
                    "IBAN cannot contain special characters."
                )
        return value
