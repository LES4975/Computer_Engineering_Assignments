from django.urls import path, include

from . import views

from django.conf.urls.static import static
from django.conf import settings

app_name = 'blog'
urlpatterns = [
    path('', views.main, name='main'),
    path('allPost/', views.allP, name="allPost"),
    path('PostDetail/<int:BlogPost_id>/', views.PostDetail, name='PostDetail'),
] + static(settings.STATIC_URL, document_root = settings.STATIC_ROOT)