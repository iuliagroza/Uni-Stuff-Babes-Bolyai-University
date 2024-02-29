from django.urls import path
from .views import AccountAPIView

urlpatterns = [
    path("account", AccountAPIView.as_view()),
    path("account/<int:pk>", AccountAPIView.as_view()),  # to capture our ids
]
