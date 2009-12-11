# Be sure to restart your server when you modify this file.

# Your secret key for verifying cookie session data integrity.
# If you change this key, all old sessions will become invalid!
# Make sure the secret is at least 30 characters and all random, 
# no regular words or you'll be exposed to dictionary attacks.
ActionController::Base.session = {
  :key         => '_Narwhal_session',
  :secret      => '1ff60eb7fb80d1776d139d61f189292f0c72b594c76666e71e8096c0d3d085e5bbd58052b641948b4cc4d61f9ef633c1cfae9e91f0ce1084b38bdea7b4b0b3aa'
}

# Use the database for sessions instead of the cookie-based default,
# which shouldn't be used to store highly confidential information
# (create the session table with "rake db:sessions:create")
# ActionController::Base.session_store = :active_record_store
