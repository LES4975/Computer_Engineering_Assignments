from django.db import models
# from django.contrib.auth.models import AbstractUser
# user객체 확장
class User():
    FirstName = models.CharField()
    phone_number = models.CharField(max_length=11)
    address = models.CharField()

class Question(models.Model):
    subject = models.CharField(max_length=200)
    content = models.TextField()
    create_date = models.DateTimeField()

    def __str__(self):
        return self.subject
class Answer(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    content = models.TextField()
    create_date = models.DateTimeField()

# 상품 모델
class Post(models.Model):
    title = models.CharField(max_length=200)
    content = models.TextField()
    create_date = models.DateTimeField()
    category = models.CharField(max_length=200)
    # user = models.ForeignKey(User, on_delete=models.CASCADE,null=False)
    price = models.IntegerField()
    image = models.ImageField(upload_to = 'images',blank=True,null=True)
    def __str__(self):
        return self.title
class Category(models.Model):
    sort = models.CharField(max_length = 255)
    def __str__(self):
        return self.sort

