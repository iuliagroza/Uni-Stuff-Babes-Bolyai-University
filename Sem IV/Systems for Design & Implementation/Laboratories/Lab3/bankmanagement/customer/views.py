from django.http.response import Http404
from django.shortcuts import render
from rest_framework import generics
from rest_framework.views import APIView
from .models import Customer
from .serializers import CustomerSerializer
from rest_framework.response import Response
from django.db.models import Count, OuterRef
from rest_framework import generics
from account.models import Account


class CustomerAPIView(APIView):
    # READ a single customer
    def get_object(self, pk):
        try:
            return Customer.objects.filter(pk=pk)
        except Customer.DoesNotExist:
            raise Http404

    def get(self, request, pk=None, format=None):
        if pk:
            data = self.get_object(pk)
        else:
            data = Customer.objects.all()

        serializer = CustomerSerializer(data, many=True)

        return Response(serializer.data)

    def post(self, request, format=None):
        data = request.data
        serializer = CustomerSerializer(data=data)

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Customer Created Successfully",
            "data": serializer.data,
        }

        return response

    def put(self, request, pk=None, format=None):
        customer_to_update = Customer.objects.get(pk=pk)
        serializer = CustomerSerializer(
            instance=customer_to_update, data=request.data, partial=True
        )

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Customer Updated Successfully",
            "data": serializer.data,
        }

        return response

    def delete(self, request, pk, format=None):
        customer_to_delete = Customer.objects.get(pk=pk)

        customer_to_delete.delete()

        return Response({"message": "Customer Deleted Successfully"})


class CustomerFilter(generics.ListAPIView):
    serializer_class = CustomerSerializer

    # Return all customers that are billionaires
    def get_queryset(self):
        return Customer.objects.filter(total_savings__gte=self.kwargs["val"])


class CustomersByNumberOfAccounts(generics.ListCreateAPIView):
    serializer_class = CustomerSerializer

    def get_queryset(self):
        query = Customer.objects.annotate(
            no_accounts=Count(
                Account.customers.through.objects.filter(customer_id=OuterRef("pk"))
                .exclude(account_id=OuterRef("accounts__id"))
                .values("account_id")
                .distinct(),
                distinct=True,
            )
        ).order_by("-no_accounts")

        print(query.query)

        return query
