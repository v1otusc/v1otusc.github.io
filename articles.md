---
layout: page
title: Articles
---
{% for post in site.posts %}    
<h3 style="text-align: left">
     <a href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a>
    <small>{{ post.date | date_to_string }}</small>
</h3>   
{% endfor %} 
