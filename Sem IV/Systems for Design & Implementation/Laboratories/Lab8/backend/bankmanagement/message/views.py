from rest_framework import viewsets
from .models import Message
from .serializers import MessageSerializer


class MessageViewSet(viewsets.ModelViewSet):
    queryset = Message.objects.all().order_by("-timestamp")
    serializer_class = MessageSerializer
