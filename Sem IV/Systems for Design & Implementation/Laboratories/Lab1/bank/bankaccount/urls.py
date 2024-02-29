from django.urls import path
from .views import BankAccountAPIView

urlpatterns = [
    path("bankaccount", BankAccountAPIView.as_view()),
    path("bankaccount/<int:pk>", BankAccountAPIView.as_view()),  # to capture our ids
]
