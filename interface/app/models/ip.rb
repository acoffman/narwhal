class Ip < ActiveRecord::Base
  belongs_to :user  
  has_many :protocols
end
