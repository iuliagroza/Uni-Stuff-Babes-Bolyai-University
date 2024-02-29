from django.http.response import Http404
from django.shortcuts import render
from rest_framework.views import APIView
from .models import BankAccount
from .serializers import BankAccountSerializer
from rest_framework.response import Response


class BankAccountAPIView(APIView):
    # READ a single bank account
    def get_object(self, pk):
        try:
            return BankAccount.objects.filter(pk=pk)
        except BankAccount.DoesNotExist:
            raise Http404

    def get(self, request, pk=None, format=None):
        if pk:
            data = self.get_object(pk)
        else:
            data = BankAccount.objects.all()

        serializer = BankAccountSerializer(data, many=True)

        return Response(serializer.data)

    def post(self, request, format=None):
        data = request.data
        serializer = BankAccountSerializer(data=data)

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Bank account created successfully.",
            "data": serializer.data,
        }

        return response

    def put(self, request, pk=None, format=None):
        bank_account_to_update = BankAccount.objects.get(pk=pk)
        serializer = BankAccountSerializer(
            instance=bank_account_to_update, data=request.data, partial=True
        )

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Bank account updated successfully.",
            "data": serializer.data,
        }

        return response

    def delete(self, request, pk, format=None):
        bank_account_to_delete = BankAccount.objects.get(pk=pk)

        bank_account_to_delete.delete()

        return Response({"message": "Bank account deleted successfully."})
