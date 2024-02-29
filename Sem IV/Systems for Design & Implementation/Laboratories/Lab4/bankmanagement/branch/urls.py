from django.urls import path
from .views import BranchAPIView

urlpatterns = [
    path("branch", BranchAPIView.as_view()),
    path("branch/<int:pk>", BranchAPIView.as_view()),  # to capture our ids
]
