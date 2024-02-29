import csv
from django.http import HttpResponse
from django.http.response import Http404
from django.shortcuts import render
from rest_framework import generics
from rest_framework.views import APIView
from .models import Customer
from .serializers import CustomerSerializer, CustomerBalanceSerializer
from rest_framework.response import Response
from rest_framework import generics
from django.db.models import Sum


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

    # Return all customers that have total amount of savings greater than a given value
    def get_queryset(self):
        return Customer.objects.filter(total_savings__gte=self.kwargs["val"])


class CustomerByTotalBalance(generics.ListAPIView):
    serializer_class = CustomerBalanceSerializer

    # Return customers sorted in descending order by their total balance (sum of balances of all their accounts)
    def get_queryset(self):
        query = Customer.objects.annotate(
            total_balance=Sum("accounts__balance")
        ).order_by("-total_balance")
        print(query.query)

        return query


class CustomerCSVExportView(APIView):
    def get(self, request, *args, **kwargs):
        # Create the HttpResponse object with the appropriate CSV header.
        response = HttpResponse(content_type="text/csv")
        response["Content-Disposition"] = 'attachment; filename="test.csv"'

        # Get all Customer objects
        customers = Customer.objects.all()

        # Create a CSV writer
        writer = csv.writer(response)

        # Write the header row
        writer.writerow(["Customer ID", "Total Savings", "Total Loans"])

        # Write data rows
        for customer in customers:
            writer.writerow([customer.id, customer.total_savings, customer.total_loans])

        return response
