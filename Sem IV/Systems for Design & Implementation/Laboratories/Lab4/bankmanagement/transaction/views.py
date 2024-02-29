from django.http.response import Http404
from django.shortcuts import render
from rest_framework import generics
from rest_framework.views import APIView
from .models import Transaction
from .serializers import TransactionSerializer
from rest_framework.response import Response


class TransactionAPIView(APIView):
    # READ a single transaction
    def get_object(self, pk):
        try:
            return Transaction.objects.filter(pk=pk)
        except Transaction.DoesNotExist:
            raise Http404

    def get(self, request, pk=None, format=None):
        if pk:
            data = self.get_object(pk)
        else:
            data = Transaction.objects.all()

        serializer = TransactionSerializer(data, many=True)

        return Response(serializer.data)

    def post(self, request, format=None):
        data = request.data
        serializer = TransactionSerializer(data=data)

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Transaction Created Successfully",
            "data": serializer.data,
        }

        return response

    def put(self, request, pk=None, format=None):
        transaction_to_update = Transaction.objects.get(pk=pk)
        serializer = TransactionSerializer(
            instance=transaction_to_update, data=request.data, partial=True
        )

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Transaction Updated Successfully",
            "data": serializer.data,
        }

        return response

    def delete(self, request, pk, format=None):
        transaction_to_delete = Transaction.objects.get(pk=pk)

        transaction_to_delete.delete()

        return Response({"message": "Transaction Deleted Successfully"})
