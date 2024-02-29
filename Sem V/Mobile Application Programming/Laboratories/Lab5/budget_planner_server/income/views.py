from asgiref.sync import async_to_sync
from channels.layers import get_channel_layer
from django.http import Http404
from rest_framework import status
from rest_framework.response import Response
from rest_framework.views import APIView
from .models import Income
from .serializers import IncomeSerializer
import logging

logger = logging.getLogger(__name__)

class IncomeListView(APIView):
    # all
    def get(self, request, *args, **kwargs):
        income = Income.objects.all()
        serializer = IncomeSerializer(income, many=True)
        return Response(serializer.data, status=status.HTTP_200_OK)

    def post(self, request, *args, **kwargs):
        serializer = IncomeSerializer(data=request.data)
        if serializer.is_valid():
            income_instance = serializer.save()
            logger.info(f"New income created: {income_instance}")
            copy_request = request.data
            copy_request['id'] = income_instance.id
            channel_layer = get_channel_layer()
            async_to_sync(channel_layer.group_send)(
                'income_updates',
                {
                    "type": 'send.income.update',
                    "data": {'type': 'create', 'income':copy_request},
                }
            )
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class IncomeDetailView(APIView):
    def get_object(self, pk):
        try:
            return Income.objects.get(pk=pk)
        except Income.DoesNotExist:
            raise Http404

    def get(self, request, pk):
        income = self.get_object(pk)
        serializer = IncomeSerializer(income)
        return Response(serializer.data)

    def delete(self, request, pk):
        income = self.get_object(pk)
        logger.info(f"Income deleted: {income}")
        income.delete()
        channel_layer = get_channel_layer()
        message = {
            "type": 'send.income.update',
            "data": {'type': 'delete', 'id': pk}
        }
        async_to_sync(channel_layer.group_send)('income_updates', message)
        print(f"Sending message: {message}")
        return Response(status=status.HTTP_204_NO_CONTENT)

    def put(self, request, pk):
        income = self.get_object(pk)
        logger.info(f"Income updated: {income}")
        serializer = IncomeSerializer(income, data=request.data)
        if serializer.is_valid():
            serializer.save()
            channel_layer = get_channel_layer()
            async_to_sync(channel_layer.group_send)(
                'income_updates',
                {
                    "type": 'send.income.update',
                    "data": {'type': 'update', 'income': request.data, 'id': pk},
                }
            )
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)