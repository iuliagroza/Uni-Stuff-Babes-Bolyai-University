from django.http.response import Http404
from django.shortcuts import render
from rest_framework.views import APIView
from .models import Bank
from .serializers import BankSerializer
from rest_framework.response import Response
from rest_framework.decorators import api_view


class BankAPIView(APIView):
    # READ a single bank
    def get_object(self, pk):
        try:
            return Bank.objects.filter(pk=pk)
        except Bank.DoesNotExist:
            raise Http404

    def get(self, request, pk=None, format=None):
        if pk:
            data = self.get_object(pk)
        else:
            data = Bank.objects.all()

        serializer = BankSerializer(data, many=True)

        return Response(serializer.data)

    def post(self, request, format=None):
        data = request.data
        serializer = BankSerializer(data=data)

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Bank created successfully.",
            "data": serializer.data,
        }

        return response

    def put(self, request, pk=None, format=None):
        bank_to_update = Bank.objects.get(pk=pk)
        serializer = BankSerializer(
            instance=bank_to_update, data=request.data, partial=True
        )

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Bank updated successfully.",
            "data": serializer.data,
        }

        return response

    def delete(self, request, pk, format=None):
        bank_to_delete = Bank.objects.get(pk=pk)

        bank_to_delete.delete()

        return Response({"message": "Bank deleted successfully."})
