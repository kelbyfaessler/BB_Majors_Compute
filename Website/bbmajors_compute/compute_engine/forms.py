from django import forms

# class UserForm(forms.ModelForm):
#     password = forms.CharField(widget=forms.PasswordInput(attrs={"class": "form-control",
#                                                                  "placeholder": "Password",
#                                                                  "required": "required"}))
#     confirm_password = forms.CharField(widget=forms.PasswordInput(attrs={"class": "form-control",
#                                                                          "placeholder": "Confirm",
#                                                                          "required": "required"}))
#     terms_conditions = forms.BooleanField(required=True,
#                                           initial=False,
#                                           widget=forms.CheckboxInput(attrs={"class": "form-check-input",
#                                                                             "type": "checkbox",
#                                                                             "id": "invalidCheck",
#                                                                             "required": "required"}))

#     class Meta:
#         model = User
#         fields = ("first_name", "last_name", "email")
#         widgets = {
#             "first_name": forms.TextInput(attrs={"class": "form-control",
#                                                  "placeholder": "First",
#                                                  "required": "required"}),
#             "last_name": forms.TextInput(attrs={"class": "form-control",
#                                                  "placeholder": "Last",
#                                                  "required": "required"}),
#             "email": forms.EmailInput(attrs={"class": "form-control",
#                                             "placeholder": "Email",
#                                             "required": "required"}),
#         }

#     def clean(self):
#         cleaned_data = super(UserForm, self).clean()

#         #check that passwords are the same
#         password = cleaned_data.get("password")
#         confirm_password = cleaned_data.get("confirm_password")
       
#         if password != confirm_password:
#             raise forms.ValidationError("password and confirmation password do not match")

#         terms_agreement = cleaned_data.get("terms_conditions")
        
#         return cleaned_data