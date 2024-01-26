from django.contrib import admin
from django.urls import path, include
# 이미지
from django.conf.urls.static import static
from django.conf import settings



from django.conf.urls.static import static
urlpatterns = [
    path('admin/', admin.site.urls),
    path('pybo/', include('pybo.urls')),
    path('common/', include('common.urls')),
]


# 방법 1.
urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
