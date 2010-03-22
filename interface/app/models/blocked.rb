class Blocked < ActiveRecord::Base
  belongs_to :users
  has_many :protocols
end