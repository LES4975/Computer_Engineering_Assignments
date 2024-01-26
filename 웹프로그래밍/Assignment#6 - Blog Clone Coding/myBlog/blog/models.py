from django.db import models

# Create your models here.
class BlogPost(models.Model):
    title = models.CharField(max_length=200)
    content = models.TextField()
    created_date = models.DateTimeField()
    updated_date = models.DateTimeField(auto_now=True, null=True)

    def __str__(self):
        return self.title