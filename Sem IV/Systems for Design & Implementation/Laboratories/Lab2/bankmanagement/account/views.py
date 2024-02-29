from django.http.response import Http404
from django.shortcuts import render
from rest_framework.views import APIView
from .models import Account
from .serializers import AccountSerializer
from rest_framework.response import Response


class AccountAPIView(APIView):
    # READ a single bank account
    def get_object(self, pk):
        try:
            return Account.objects.filter(pk=pk)
        except Account.DoesNotExist:
            raise Http404

    def get(self, request, pk=None, format=None):
        if pk:
            data = self.get_object(pk)
        else:
            data = Account.objects.all()

        serializer = AccountSerializer(data, many=True)

        return Response(serializer.data)

    def post(self, request, format=None):
        data = request.data
        serializer = AccountSerializer(data=data)

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Account created successfully.",
            "data": serializer.data,
        }

        return response

    def put(self, request, pk=None, format=None):
        account_to_update = Account.objects.get(pk=pk)
        serializer = AccountSerializer(
            instance=account_to_update, data=request.data, partial=True
        )

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Account updated successfully.",
            "data": serializer.data,
        }

        return response

    def delete(self, request, pk, format=None):
        account_to_delete = Account.objects.get(pk=pk)

        account_to_delete.delete()

        return Response({"message": "Account deleted successfully."})
