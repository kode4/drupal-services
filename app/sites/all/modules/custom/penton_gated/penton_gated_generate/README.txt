Welcome to Penton Gated generate

This module generates content which is exploitable easily for the Penton project in the context of gated content.

It is meant to be used for development and testing purposes. DO NOT ENABLE THIS MODULE ON PRODUCTION!

It provides by default the following:

* Users (login / password):
basic / basic (User with role "authenticated user")
advanced / advanced (User with role "advanced registered user")

* Taxonomy terms
One term in the "Categories" vocabulary with title "Category"
One term in the "Program" vocabulary with title "Program"

* Content
** Articles
*** Unpinned
One ungated article with title "Ungated article"
One basic gated article with title "Basic gated article"
One advanced gated article with title "Advanced gated article"
>> These three articles are attached to the Category and Program terms

*** Pinned
One ungated article pinned to the Category term with title "Ungated article pinned to Category"
One ungated article pinned to the Program term with title "Ungated article pinned to Program"

** Comments
Articles will get a total of max 5 comments from random users.