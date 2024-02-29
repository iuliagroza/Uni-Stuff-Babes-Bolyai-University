from django.http.response import Http404
from django.shortcuts import render
from rest_framework.views import APIView
from .models import Branch
from .serializers import BranchSerializer
from rest_framework.response import Response


class BranchAPIView(APIView):
    # READ a single branch
    def get_object(self, pk):
        try:
            return Branch.objects.filter(pk=pk)
        except Branch.DoesNotExist:
            raise Http404

    def get(self, request, pk=None, format=None):
        if pk:
            data = self.get_object(pk)
        else:
            data = Branch.objects.all()

        serializer = BranchSerializer(data, many=True)

        return Response(serializer.data)

    def post(self, request, format=None):
        data = request.data
        serializer = BranchSerializer(data=data)

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Branch created successfully.",
            "data": serializer.data,
        }

        return response

    def put(self, request, pk=None, format=None):
        branch_to_update = Branch.objects.get(pk=pk)
        serializer = BranchSerializer(
            instance=branch_to_update, data=request.data, partial=True
        )

        serializer.is_valid(raise_exception=True)

        serializer.save()

        response = Response()

        response.data = {
            "message": "Branch updated successfully.",
            "data": serializer.data,
        }

        return response

    def delete(self, request, pk, format=None):
        branch_to_delete = Branch.objects.get(pk=pk)

        branch_to_delete.delete()

        return Response({"message": "Branch deleted successfully."})
