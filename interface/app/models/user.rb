class User < ActiveRecord::Base
  has_many :ips
end
