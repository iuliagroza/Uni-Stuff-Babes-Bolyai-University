from django.urls import path
from .views import TransactionAPIView

urlpatterns = [
    path("transaction", TransactionAPIView.as_view()),
    path("transaction/<int:pk>", TransactionAPIView.as_view()),  # to capture our ids
]
