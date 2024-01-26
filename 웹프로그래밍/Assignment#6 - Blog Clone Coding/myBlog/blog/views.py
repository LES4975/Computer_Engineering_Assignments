from django.shortcuts import render
from django.utils import timezone
# Create your views here.
from django.shortcuts import render, get_object_or_404
from .models import BlogPost
from django.http import HttpResponse
from django.core.paginator import Paginator

def index(request):
    return HttpResponse("Test it")

def main(request):
    Post_list = BlogPost.objects.order_by('-created_date')
    paginator = Paginator(Post_list, 3)
    page_obj = paginator.get_page(1)
    context = {'Post_list': page_obj}
    return render(request, 'blog/main.html', context)

def allP(request):
    Post_list = BlogPost.objects.order_by('-updated_date')
    context = {'Post_list' : Post_list}
    return render(request, 'blog/allPost.html', context)

def PostDetail(request, BlogPost_id):
    # post = BlogPost.objects.get(id=BlogPost_id)
    post = get_object_or_404(BlogPost, pk=BlogPost_id)
    context = {'post': post}
    return render(request, 'blog/PostPage.html', context)